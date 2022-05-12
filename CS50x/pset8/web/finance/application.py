import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

firstLogin = True

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = []

    user = (db.execute("SELECT * FROM users WHERE id=:id", id=session['user_id']))[0]

    global firstLogin

    rows += (db.execute("SELECT * FROM transactions WHERE id=:id", id=session['user_id']))

    if firstLogin:
        username = user["username"]
        flash(f"Welcome, {username}!")
        firstLogin = False

    total = round(user["cash"] + sum([row["price"] * row["shares"] for row in rows]), 2)

    return render_template("index.html", cash=user["cash"], total=total, rows=rows)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get the form data and store it in variable
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if (not symbol) or (not lookup(symbol)):
            return apology("missing symbol", 406)
        if shares <= 0:
            return apology("missing shares", 407)

        data = lookup(symbol)

        id = session["user_id"]

        price = data["price"]

        cost = round(shares * price, 2)

        companyname = data["name"]
        if companyname == "":
            companyname = "-"

        dt = datetime.datetime.now()

        cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session['user_id'])[0]["cash"]

        # Added table already
        # db.execute("CREATE TABLE transactions (id INTEGER NOT NULL, symbol TEXT NOT NULL, companyname TEXT NOT NULL, shares INTEGER NOT NULL, price NUMERIC NOT NULL, ttime DATETIME NOT NULL);")

        # Ensure that enough cash is there in users account
        if cost > cash:
            return apology("insufficient cash", 408)

        db.execute(
            "INSERT INTO transactions (id, symbol, companyname, shares, price, ttime) VALUES (:id, :symbol, :companyname, :shares, :price, :dt)",
            id=id, symbol=symbol, companyname=companyname, shares=shares, price=price, dt=dt)

        cash = round(cash - cost, 2)
        print(cash)

        db.execute("UPDATE users SET cash=:cash", cash=cash)

        flash("Bought!")

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 401)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 402)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/login")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get the form data and store it in variable
        symbol = request.form.get("symbol")

        # If lookup did not return None, then render quoted information
        if symbol and lookup(symbol):

            # Storing JSON data in data
            data = lookup(symbol)

            # Rendering quoted.html showing the latest price of that particular share
            return render_template("quoted.html", symbol=data["symbol"], price=data["price"])

        # Ensuring that valid symbol is quoted
        else:
            return apology("missing symbol", 406)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get the form data and store it in variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 401)

        # Ensure password was submitted
        elif not "password":
            return apology("must provide password", 402)

        # Ensure confirmation password was submitted
        elif not confirmation:
            return apology("must provide confirmation password", 402)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)

        # Ensure username is not taken already
        if len(rows):
            return apology("username already taken", 404)

        # Ensuring that password and confirmation password match
        elif password != confirmation:
            return apology("passwords did not match", 405)

        # Query for inserting username and hashed password to users table in database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username,
                   hash=generate_password_hash(password))

        id = db.execute("SELECT id FROM users WHERE username = :username", username=username)[0]["id"]
        print(id)

        session["user_id"] = id

        flash("Registered!")

        # Redirect to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

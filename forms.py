from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField, BooleanField, IntegerField, FloatField
from wtforms.validators import DataRequired, Length, Email, EqualTo, NumberRange


class RegistrationForm(FlaskForm):
    username = StringField('Username', validators = [DataRequired(), Length(min = 2, max = 20)])
    email = StringField('Email', validators = [DataRequired(), Email()])
    password = PasswordField('Password', validators = [DataRequired()])
    confirm_password = PasswordField('confirm_password', validators = [DataRequired(), EqualTo('password')])
    submit = SubmitField("Sign_up")
    
class LoginForm(FlaskForm):
    email = StringField('Email', validators = [DataRequired(), Email()])
    password = PasswordField('Password', validators = [DataRequired()])
    remember = BooleanField('Remember ME')
    submit = SubmitField('Login')

class ApplyForm(FlaskForm):
    username = StringField('Username:', validators = [DataRequired(), Length(min = 2, max = 20)])
    user_credit_score = IntegerField('Enter your Credit Score:', validators = [DataRequired(), NumberRange(min = 50, max = 850) ])
    user_monthly_income = FloatField('Enter your Monthly Income:', validators = [DataRequired(), NumberRange(min = 800, max = 30000)])
    user_financial_reserves = FloatField('Enter your Financial Reserves Valuation:', validators = [DataRequired(), NumberRange(min = 50000, max = 2000000)])
    user_debt_to_income_ratio = FloatField('Enter your debt to income ratio as a percentage of your yearly income eg enter "12" for 12 percent:', validators = [DataRequired(), NumberRange(min = -500, max = 500)])
    user_loan_amoumnt_requested = FloatField('Enter the amount you want to borrow:', validators = [DataRequired(), NumberRange(min = 100, max = 500000)])
    user_loan_duration = IntegerField('Enter the duration of the loan in months:', validators = [DataRequired(), NumberRange(min = 10, max = 240)])
    
    submit = SubmitField('Submit')
    
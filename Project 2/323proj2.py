# Need for regular expressions
import re
import sys

plus_minus = ['+', '-']
multi_div = ['*', '/']

# Created a Class Parser with member functions
class Parser():
  def __init__(self, expression):
    self.input = expression
    """ \d+ references: https://stackoverflow.com/questions/2841550/what-does-d-mean-in-a-regular-expression
        https://stackoverflow.com/questions/40053653/python-regular-expression-d """
    # Finds all operators in given expression and returns
    self.tokens = re.findall('\d+|\+|\-|\*|\/|\(|\)', expression)
    self.index = 0

  def check_parenthesis(self):
    if self.index < len(self.tokens):
      if self.tokens[self.index] == '(':
        self.index = self.index + 1
        result = self.op_plus_minus()
        self.check_token(')')
        return result
      elif self.tokens[self.index].isdigit():
#        if self.tokens[self.index - 1] == '-':
#           result = int(self.tokens[self.index]) * -1
#           self.index = self.index + 1
#           return result
#        else:
           result = int(self.tokens[self.index])
           self.index = self.index + 1
           return result
    self.invalid_msg()

  def check_token(self, input_token):
    """ Checks if the input token matches with the current position """
    if self.index < len(self.tokens) and self.tokens[self.index] == input_token:
       self.index += 1
    else:
       self.invalid_msg()

  def op_plus_minus(self):
     """ Deals with + and - operands """
     # * and / have precedence over + and -
     # Getting the first number
     result = self.op_multi_div()
     while self.index < len(self.tokens) and self.tokens[self.index] in plus_minus:
       current_operator = self.tokens[self.index]
       self.index = self.index + 1
       # Getting the next number
       temp = self.op_multi_div()
       if current_operator == '+':
          result = int(result + temp)
       if current_operator == '-':
          result = int(result - temp)
     return result

  def op_multi_div(self):
    """ Deals with * and / operands """
    result = self.check_parenthesis()
    while self.index < len(self.tokens) and self.tokens[self.index] in multi_div:
       current_operator = self.tokens[self.index]
       self.index = self.index + 1
       temp = self.check_parenthesis()
       if current_operator == '*':
           result = int(result * temp)
       else:
           result = int(result / temp)
    return result

  def invalid_msg(self):
      """ Function that is called to end the program when an invalid expression is encountered"""
      print("Entered expression is invalid!")
      sys.exit()


user_input = input("Enter the expression\n")
recur_desc_parser = Parser(user_input)
print("Result =", recur_desc_parser.op_plus_minus())
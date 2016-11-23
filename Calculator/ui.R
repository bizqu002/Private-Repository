
# Author: Brenda S. Izquierdo
# PID: 3886796
#


library(shiny)

shinyUI(fluidPage(
    
    titlePanel("Calculator"),
  
    sidebarLayout(sidebarPanel(
      
      tags$style(".well {background-color:#ecf2f9;}"),
      
     strong(uiOutput("operand1")),
      
      numericInput(
        inputId = "num1",
        label = "",
        value = "0"
      ),
      
     radioButtons(
       inputId = "radio", 
       label = "",
       choices = list("Deg" = 1, "Rad" = 2), 
       selected = 2
     ),
     
     actionButton(
       inputId = "memory_recall", 
       label = "MR", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #FF8C00; border-color: #2e6da4"
     ),  
     
     actionButton(
       inputId = "memory_store", 
       label = "MS", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #FF8C00; border-color: #2e6da4"
     ),  
     
     actionButton(
       inputId = "add_to_memory", 
       label = "M+", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #FF8C00; border-color: #2e6da4"
     ),  
     
     actionButton(
       inputId = "subtract_from_memory", 
       label = "M-", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #FF8C00; border-color: #2e6da4"
     ),  
     
     actionButton(
       inputId = "clear_memory", 
       label = "MC", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #FF8C00; border-color: #2e6da4"
     ),  
     
     actionButton(
       inputId = "sine", 
       label = "sin", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #397D02; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "cosine", 
       label = "cos", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #397D02; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "tangent", 
       label = "tan", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #397D02; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "arcsine", 
       label = "arcsin", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #397D02; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "arccosine", 
       label = "arccos", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #397D02; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "arctangent", 
       label = "arctan", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #397D02; border-color: #2e6da4"
     ), 
     
      div(style="display:inline-block;",uiOutput("plus")),
      div(style="display:inline-block;",uiOutput("minus")),
      div(style="display:inline-block;",uiOutput("asterisk")),
      div(style="display:inline-block;",uiOutput("dash")),
     
     actionButton(
       inputId = "negative", 
       label = "(-)", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #ff7f50; border-color: #2e6da4"
     ), 
     
     
     actionButton(
       inputId = "equal", 
       label = "=", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #ff7f50; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "inverse", 
       label = "1/x", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "clear", 
       label = "CE", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
      actionButton(
        inputId = "reset", 
        label = "C", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #D83000; border-color: #2e6da4"
      ),  
     
     actionButton(
       inputId = "open_parenthesis", 
       label = "(", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),  
   
     actionButton(
       inputId = "close_parenthesis", 
       label = ")", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),  
     
    
     actionButton(
       inputId = "pi", 
       label = "π", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "e", 
       label = "e", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "xtoy", 
       label = "x^y", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "xtotwo", 
       label = "x^2", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "xtothree", 
       label = "x^3", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "etox", 
       label = "e^x", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "tentox", 
       label = "10^x", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "yrootofx", 
       label = "y√x", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "cubicrootofx", 
       label = "3√x", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ), 
     
     actionButton(
       inputId = "quadraticrootofx", 
       label = "√x", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "ln", 
       label = "ln", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "log", 
       label = "log", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "percent", 
       label = "%", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "factorial", 
       label = "n!", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),
     
     actionButton(
       inputId = "EXP", 
       label = "EXP", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),  
     
     actionButton(
       inputId = "RND", 
       label = "RND", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #D83000; border-color: #2e6da4"
     ),  
     
      actionButton(
        inputId = "one", 
        label = "1", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),  
      actionButton(
        inputId = "two", 
        label = "2", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),  
      actionButton(
        inputId = "three", 
        label = "3", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      
      actionButton(
        inputId = "four", 
        label = "4", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      actionButton(
        inputId = "five", 
        label = "5", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      actionButton(
        inputId = "six", 
        label = "6", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      actionButton(
        inputId = "seven", 
        label = "7", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      actionButton(
        inputId = "eight", 
        label = "8", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      actionButton(
        inputId = "nine", 
        label = "9", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      actionButton(
        inputId = "zero", 
        label = "0", 
        icon = NULL, 
        width = NULL,
        length = NULL,
        style="color: #fff; background-color: #003399; border-color: #b3ccff"
      ),
      
     actionButton(
       inputId = "decimal", 
       label = ".", 
       icon = NULL, 
       width = NULL,
       length = NULL,
       style="color: #fff; background-color: #003399; border-color: #b3ccff"
     )  
      
      ),
    
    mainPanel(
      
    ))
))
import re

# Read the HTML file
with open('test.html', 'r') as file:
    html_content = file.read()

# Use regex to remove content between tags
cleaned_html = re.sub(r'>[^<]+<', '><', html_content)

# Optionally, save the result to a new file
with open('cleanedtest.html', 'w') as file:
    file.write(cleaned_html)

# Print the result or use as needed
print(cleaned_html)

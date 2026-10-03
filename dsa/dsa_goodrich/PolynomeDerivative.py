import re

def parse_term(term):
    """
    Parses a single term (e.g., '3x^2', '-x', '+2*x', '5') into (coefficient, exponent).
    Constants are returned as (0, 0) because their derivative is zero.
    """
    # Pattern: sign, coefficient, optional '*', optional 'x', optional '^exponent'
    match = re.match(r'([+-]?)(\d*)(?:\*?)(x?)(?:\^(\d+))?', term)
    if not match:
        return 0, 0

    sign = match.group(1)          # '+', '-', or ''
    coeff_str = match.group(2)     # digits or ''
    has_x = match.group(3) == 'x'  # True if variable present
    exp_str = match.group(4)       # digits or None

    if has_x:
        # If coefficient is omitted, default to 1
        coeff = 1 if coeff_str == '' else int(coeff_str)
        if sign == '-':
            coeff = -coeff
        # If exponent is omitted, default to 1
        exp = 1 if exp_str is None else int(exp_str)
        return coeff, exp
    else:
        # Constant term (e.g., '5' or '-3')
        return 0, 0

def format_derivative(terms):
    """
    Formats a list of (coefficient, exponent) pairs into a human-readable string.
    Handles special cases for coefficient 1, -1, exponent 0, and 1.
    """
    if not terms:
        return "0"

    result_parts = []
    for i, (coeff, exp) in enumerate(terms):
        abs_coeff = abs(coeff)

        # Build the term string without the sign
        if exp == 0:
            part = str(abs_coeff)
        elif exp == 1:
            part = "x" if abs_coeff == 1 else f"{abs_coeff}x"
        else:
            part = f"x^{exp}" if abs_coeff == 1 else f"{abs_coeff}x^{exp}"

        # Attach the sign
        if coeff < 0:
            part = "-" + part if i == 0 else " - " + part
        else:
            part = part if i == 0 else " + " + part

        result_parts.append(part)

    return "".join(result_parts)


def derivative(poly_str):
    """
    Computes the first derivative of a polynomial given as a string.
    """
    # Remove all spaces for easier parsing
    poly_str = poly_str.replace(" ", "")
    if not poly_str:
        return "0"

    # Split into terms keeping the leading sign with each term
    # e.g., "3x^2+2x-5" -> ['3x^2', '+2x', '-5']
    terms = re.findall(r'[+-]?[^+-]+', poly_str)

    derivative_terms = []
    for term in terms:
        coeff, exp = parse_term(term)
        if coeff == 0:
            continue  # constants vanish in the derivative

        # Power rule: d/dx [c * x^n] = (c * n) * x^(n-1)
        new_coeff = coeff * exp
        new_exp = exp - 1
        if new_coeff != 0:
            derivative_terms.append((new_coeff, new_exp))

    return format_derivative(derivative_terms)


if __name__ == "__main__":
    poly = input("Enter a polynomial (e.g., 3x^2 + 2x - 5): ")
    result = derivative(poly)
    print(f"The derivative is: {result}")
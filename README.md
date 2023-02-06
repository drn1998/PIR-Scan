# pircode
Implementation of PIR codes in different langauges

Every implemenation needs a method/function/way to match a string against a PIR code. This should not only account for full PIR codes (five decimal digits) but also shortened PIR codes (only first n digits) such as "83" or "8" and codes that refer to substrings, prefixes or suffixes:

6_31  A six-character prefix of the word (words shorter than 6 characters are ignored) has a PIR code starting with 31
6/31  The word contains a sequence of 6 characters with a PIR code starting with 31. The method may also be offered with an option to exclude implausable substrings (e.g. decarbonization has the plausible substring 'carbon' but not 'nizati'), although this is non-trivial and may have false-negatives.
31s With rule-based trivial stemming. For german language, this might be removing any suffix of "n", "en", "e", "r", "er", "s", "innen", "_innen", "*innen", "es". The user has to make sure themself that a singular is not damaged when using this mode

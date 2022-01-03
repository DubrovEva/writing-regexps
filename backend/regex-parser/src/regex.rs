use crate::char::NaiveChar;
use crate::utils::Range;

#[derive(Debug, Clone, Eq, PartialEq)]
pub struct Regex<C> {
    pub parts: Vec<RegexPart<C>>,
}

#[derive(Debug, Clone, Eq, PartialEq)]
pub enum RegexPart<C> {
    Literal(C),
    Alternatives(Vec<RegexPart<C>>),
    Bracketed(Bracketed<C>),
    ParenGroup { capture: Option<Capture>, inner: Box<RegexPart<C>> },
    LineStart,
    LineEnd,
    Optional(Box<RegexPart<C>>),
    ZeroOrMore { eagerness: Eagerness, inner: Box<RegexPart<C>> },
    OneOrMore { eagerness: Eagerness, inner: Box<RegexPart<C>> },
    Repeat { eagerness: Eagerness, n: RepeatSpec, inner: Box<RegexPart<C>> },
}

#[derive(Debug, Clone, Eq, PartialEq)]
pub struct Bracketed<C> {
    pub alternatives: Vec<BracketedAlternative<C>>,
}

#[derive(Debug, Clone, Eq, PartialEq, Hash)]
pub enum BracketedAlternative<C> {
    Single(C),
    Range(Range<C>),
}

#[derive(Debug, Clone, Eq, PartialEq, Hash)]
pub enum Capture {
    Index,
    Name(String),
}

#[derive(Debug, Copy, Clone, Eq, PartialEq, Hash)]
pub enum Eagerness {
    Greedy,
    Lazy,
    Possessive,
}

#[derive(Debug, Copy, Clone, Eq, PartialEq, Hash)]
pub enum RepeatSpec {
    Exactly(usize),
    AtLeast(usize),
    AtMost(usize),
    Range(Range<usize>),
}

pub type NaiveRegex = Regex<NaiveChar>;
pub type NaiveRegexPart = RegexPart<NaiveChar>;
pub type NaiveBracketed = Bracketed<NaiveChar>;
pub type NaiveBracketedAlternative = BracketedAlternative<NaiveChar>;

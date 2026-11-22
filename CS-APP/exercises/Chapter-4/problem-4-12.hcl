
/* Practice Problem 4.12 (solution page 520)
Write HCL code describing a circuit that for word inputs A, B, and C selects the
median of the three values. That is, the output equals the word lying between the
minimum and maximum of the three inputs. */

word median = [
  (B >= A && A >= C) || (C >= A && A >= B) : A;
  (A >= B && B >= C) || (C >= B && B >= A) : B;
  1 : C;
];

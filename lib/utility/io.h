static ll scanner_ll() {
	ll x = 0, f = 1, c;
	while (c = getchar_unlocked(), c < 48 || c > 57) if (c == 45) f = -f;
	while (47 < c && c < 58) {
		x = x * 10 + c - 48;
    	c = getchar_unlocked();
	}
	return f * x;
}

static ll* scanner_ll_multi(int n) {
	ll* res = (ll*)malloc(n*sizeof(ll));
	for (int i=0;i<n;++i) res[i] = scanner_ll();
	return res;
}

static char* scanner_string(int n) {
	char* res = (char*)malloc((n+1)*sizeof(char));
	char c = getchar_unlocked();
	while (c < 32) c = getchar_unlocked();
	int i = 0;
	while (c >= 32) {
    	res[i] = c;
    	c = getchar_unlocked();
    	i++;
	}
	res[i] = '\0';
	return res;
}

static void printer_ll(ll x) {
	if (x < 0) {
		putchar_unlocked('-');
		x = -x;
	}
	if (x >= 10) {
    	printer_ll(x / 10);
	}
  	putchar_unlocked(x - x / 10 * 10 + 48);
}

static void printer_ll_one(ll x) {
    printer_ll(x);
    putchar_unlocked('\n');
}

static void printer_ll_array_v(ll* x, int n) {
    for (int i=0;i<n-1;++i) {
        printer_ll(x[i]);
        putchar_unlocked(' ');
    }
    printer_ll(x[n-1]);
    putchar_unlocked('\n');
}

static void printer_ll_array_h(ll* x, int n) {
    for (int i=0;i<n;++i) {
        printer_ll(x[i]);
        putchar_unlocked('\n');
    }
}

static void printer_string(char* x, int n) {
    int i = 0;
	while (x[i]!='\0' && i<n) {
		putchar_unlocked(x[i]);
		++i;
	}
	putchar_unlocked('\n');
}
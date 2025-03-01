/*
 User Extensions
*/
  
// Definitions
object *fn_setdisplay (object *args, object *env) {
#if defined(gfxsupport)
  (void) env;
  int nargs = listlength(args);
  int display_num;
  // Set display
  if (nargs == 1) {
    display_num = checkinteger(first(args));
    if (display_num == 1) {
      tftp = &tft1;
    }
    else if (display_num == 2) {
      //tftp = &tft2;
    }
  } else error2(PSTR("wrong number of arguments"));
  
  return nil;
#else
  (void) args, (void) env;
  error2(PSTR("not supported"));
  return nil;
#endif
}

object *sp_withdisplay (object *args, object *env) {
#if defined(gfxsupport)
  (void) env;
  int nargs = listlength(args);
  int display_num;
  // Set display
  if (nargs == 2) {
    Adafruit_GFX *oldtftp = tftp;
    display_num = checkinteger(first(args));
    if (display_num == 1) {
      tftp = &tft1;
    }
    else if (display_num == 2) {
//      tftp = &tft2;
    }
    object *forms = cdr(args);
    object *result = eval(tf_progn(forms,env), env);
    tftp = oldtftp;
    return result;
  } else error2(PSTR("wrong number of arguments"));

#else
  (void) args, (void) env;
  error2(PSTR("not supported"));
  return nil;
#endif
}

object *sp_withlog (object *args, object *env) {
#if defined(gfxsupport)
  object *params = first(args);
  object *var = first(params);
  object *pair = cons(var, stream(LOGSTREAM, 1));
  push(pair,env);
  object *forms = cdr(args);
  object *result = eval(tf_progn(forms,env), env);
  return result;
#else
  (void) args, (void) env;
  error2(PSTR("not supported"));
  return nil;
#endif
}


// Symbol names
const char stringsetdisplay[] PROGMEM = "set-display";
const char stringwithdisplay[] PROGMEM = "with-display";
const char stringwithlog[] PROGMEM = "with-log";

// Documentation strings
const char docsetdisplay[] PROGMEM = "(set-display num)\n"
  "Sets the current display to display # num";
const char docwithdisplay[] PROGMEM = "(with-display num form*)\n"
  "Evaluates forms with the current display set to display # num";
const char docwithlog[] PROGMEM = "(with-log (str) form*)\n"
"Evaluates the forms with str bound to a log-stream so you can print text\n"
"to the log display using the standard uLisp print commands.";

// Symbol lookup table
const tbl_entry_t lookup_table2[] PROGMEM = {
  { stringsetdisplay, fn_setdisplay, 0211, docsetdisplay },
  { stringwithdisplay, sp_withdisplay, 0322, docwithdisplay },
  { stringwithlog, sp_withlog, 0317, docwithlog },};

// Table cross-reference functions

tbl_entry_t *tables[] = {lookup_table, lookup_table2};
const unsigned int tablesizes[] = { arraysize(lookup_table), arraysize(lookup_table2) };

const tbl_entry_t *table (int n) {
  return tables[n];
}

unsigned int tablesize (int n) {
  return tablesizes[n];
}

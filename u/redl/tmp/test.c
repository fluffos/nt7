inherit ITEM;

string a = "";

void set_value(string b)
{
    a = b;
}

void query_value()
{
   write("value:" + a + "\n");
    if (a) write("true\n");
      else write("false\n");
    
}
void test_callout() 
{
call_out((:call_other(load_object("/u/redl/prison.c"), "chk2sgl", find_player("red")):), 9); 
}

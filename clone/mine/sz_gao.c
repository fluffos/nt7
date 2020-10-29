// sz_gao.c

inherit ITEM;

protected int mangle = 100;
int is_mine_tool() { return 1; }
int tool_can_use() { return (mangle > 0); }
int no_save_in_home() { return 1; }
string query_long()
{
        if(mangle > 0)
                return "这是一把挖掘用的十字镐。\n";
        else
                return "这是一把坏掉的十字镐。\n";
}

void create()
{
        set_name("十字镐", ({ "shizi gao" }) );
        set_weight(2000);
        set("unit", "把");
        set("long", (: query_long :));
        set("value", 500);
}

void use_this_tool()
{
        if( (--mangle <= 0) && environment() )
                tell_object(environment(), "\n十字镐坏了。\n\n");
        set("value", 0);
}
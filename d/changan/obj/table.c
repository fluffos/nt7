inherit ITEM;

void create()
{
        set_name( "桌子",({"table" }));
        set_weight(30000);
        set_max_encumbrance(18000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("material", "wood");
                set("value", 2000);
                set("long", "这张破桌子放在这里很久了，上面放了一个八卦盘，和一个签筒。\n" );
                set("no_sell", "这样东西不能随便买卖。");
        }
        setup();
}
void init()
{
        add_action("do_look","see");
        add_action("do_get","get");
}
int do_look(string arg)
{
        object ob, who;
        ob = this_object();
        who = this_player();
        if(!arg || arg !="table")
                return notify_fail("你要看什么? \n");
        else   return notify_fail("赛半仙正趴在桌子上睡觉呢，看来你要（knock）桌子才能叫醒他了。\n");
}
int do_get(string arg)
{
        object ob, me;
        ob = this_object();
        me = this_player();
        if(arg && arg =="table"){
                write ("不要搞恶作剧好不好，那是赛半仙唯一的财产了。\n");
                 return 1;
        }
        return 0;
}

#include <ansi.h>

inherit ITEM;

string get_long();

void create()
{
        set_name( "竹签", ({ "zhu qian", "qian"}) );
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", (:get_long:));
                set("value", 0);
                set("material", "wood");
        }
        setup();
}

string get_long()
{
        string long;
        mapping qianwen;

        qianwen = query("qianwen");

        if( !mapp(qianwen) || query("owner") != query("id", this_player()) )
                return "一根狭长的竹签，上面用朱砂题了两行小字，看不太真切。\n";

        long = "一根狭长的竹签，上面题了几行小字：\n";
        long += "                "+HIW +"〖"+ qianwen["title"] + "〗\n" + NOR;
        long += HIM + qianwen["doc"] + "\n" + NOR;
        return long;
}

void csh_qianwen()
{
        set("qianwen","/d/city/npc/qianwen/qianwen"->get_qian());
        set("long",(:get_long:));
        return;
}
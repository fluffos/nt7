// /d/xiakedao/obj/tongpai1.c
//edit by noz
// Modified by Zeratul Jan 11 2001 铜牌退出时不丢，不能给人
/*
#include <ansi.h>
inherit ITEM;

void create()
{
          set_name( "罚恶铜牌",({"e pai"}));
          set_weight(100);

          if( clonep() )
                set_default_object(__FILE__);

          set("unit", "块");
          set("long", "这是一块闪闪发光的白铜片子，约有巴掌大小，牌子正面刻着一张狰狞的煞神凶脸，十分诡异。\n" );
        set("no_put",1);
        set("no_get",1);
        set("no_drop",1);
        set("no_beg",1);
        set("no_steal",1);

          setup();
}

string query_autoload()
{
        if( query("own") != query("id", this_player()) )
                return 0;
        if( time()>query("xkd/time", this_player()) )
                return 0;
        return query("own");
}

void autoload(string param)
{
        string owner;

        if ( !objectp( this_object() ) )
                return;
        if( time()>query("xkd/time", this_player()) )
        {
                destruct( this_object() );
                return;
        }
        if( sscanf(param, "%s", owner)==1 )
                set( "own", owner );
}

int init()
{
        stringlong_msg=query("long", this_object());

          if( query("xkd/time", this_player()) )
                  long_msg+=HIC"牌子背面刻得有字：侠客岛于"+CHINESE_D->chinese_date(((query("xkd/time", this_player())-950000000)*60))+"前恭候大驾。\n"NOR;
          set("long", long_msg, this_object());
        return 1;
}
*/

//tongpai1.c
//edit by noz

inherit ITEM;

void create()
{
        set_name("罚恶铜牌",({ "e pai" }));
        set_weight(100);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", "这是一块闪闪发光的白铜片子，约有巴掌大小，牌子正"
                            "面刻着一张狰狞的煞神凶脸，十分诡异。\n");
                set("value", 100);
        }

        setup();
}
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "枫林渡");
        set("long",
"这里是前往绿柳山庄的必经之路，一道小河横在你的面前，上面结了\n"
"薄薄的一层冰。渡口旁边一条破烂的布幅订在树上，白布在北风中飞舞，\n"
"你定睛一看，上面写着几个血字：\n"
HIR "                    一入此境，便无归路\n" NOR
);

        set("exits", ([ /* sizeof() == 2 */
          "south" : __DIR__"inn",
          "north" : __DIR__"xueyuan",
        ]));    
        set("no_fight",1);                                 
       set ("no_look",1);
        setup();
}                                  

int init()
{
          add_action("do_north","gonorth");
}                

int valid_leave(object me,string dir)
{
        if( dir == "north" )
                return notify_fail(
                        "\n你要过去吗？你真的要过去吗？你该不是真想要过去吧。\n"        
                        "想要过去就说嘛。虽然你很有诚意的样子徘徊在这里，\n"
                        "可是你不说别人怎么知道你要过去呢？你真的要过去吗？\n"
                          "想要过去你就敲gonorth吧。\n\n"
                );
        return 1;
}

int do_north(string arg)
{
        object me;
        object *inv;
        int i;

        me = this_player();

        inv = all_inventory(me);
        for( i=0;i<sizeof(inv);i++) 
        {
                if( inv[i]->is_character() )
                {
                        write("你不能背着"+query("name", inv[i])+"进去!\n");
                        return 1;
                }
        }

        if( query("combat_exp", me)<2000000 )
        {       
                write(RED"前方路途险恶，还是不要去送死了吧。\n"NOR);
                return 1;
        }

        write(YEL"你鼓足勇气，渡过河去，踏上了险恶的征程。\n"NOR);
        this_player()->move(__DIR__"xueyuan");

        return 1;
}

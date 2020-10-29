#include <ansi.h>
inherit ITEM;

void create()
{
                
        set_name(HIG"原始森林入口"NOR, ({ "forest door","door"}) );
        set_weight(5);
        set("no_get",1);

        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", GRN"从这个入口可以进入原始森林迷宫副本。(enter door)\n"NOR); 
                set("unit", "个");
                set("lore",1);
                set("value", 20);
        }
        setup();
}
void init()
{
        add_action("do_enter","enter");
}

/*
int do_enter(string arg) {
        if (arg!="door")
                return 0;

        MAZE_D->enter_virtual_maze(this_player(), "forest");
        return 1;
}
*/

int do_enter(string arg) 
{
        int valid;
                
        if( !arg || (arg != "door" && arg != "forest") )
                return 0;
        
        arg = "forest";
        valid = FUBEN_D->valid_enter(this_player(), arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(this_player(), arg);
        else {
                if( valid == 0 )
                        write("您实战经验不足，进副本恐有不测，还是先历练一下再来吧。\n");
                else if( valid == -1 )
                        write("您经验太高了，就不要进去欺负那些可怜的小怪物了吧。\n");
                else if( valid == -2 )
                        write("游戏中目前并没有开放该副本，请您核对后再试。\n");
                else if( valid == -3 )
                        write("该副本限制IP多重进入，您已经超过最高上限。\n");
                else if( valid == -4 )
                        write("该副本被巫师关闭，您暂时无法进入。\n");

        }        
        return 1;
}


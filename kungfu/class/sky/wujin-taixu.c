
#include <ansi.h>

inherit ITEM;

void setup()
{

        set("no_clean_up", 1);
        set("no_roar", 1);
        set("no_flyto", 1);    // 不能骑马或MISS到这里，已经在horse.c做限制
        set("no_rideto", 1);   // 不能骑马或MISS到这里，已经在horse.c做限制
        set("no_obsend", 1);
        set("no_paimai", 1);

        ::setup();

}

void create()
{
        set_name(HIW "无尽太虚" NOR, ({ "wujin taixu" }));
        set_weight(200000);
        set_max_encumbrance(2000000000);

        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else
        {
                set("value", 1);
                set("long",
                HIY "这里是宇宙之深渊，无尽的太虚，四周白茫茫一片，似乎没有前进之路，\n"
                    "也没有边际。不时有阵阵琴音传出，幽雅而又意味深长，令你不禁回想起这\n"
                    "一生，经过了多少恩怨情仇，经过了多少血腥与杀戮，在这浩瀚无边际的宇\n"
                    "宙之中，你只不过是一粒细小的尘埃，亦或在上天众神眼中你只不过是一只\n"
                    "微不足道的蝼蚁 …… 琴音时而委婉，时而高亢，随着琴音起伏，你心中思\n"
                    "绪万千 ……\n"NOR);
                set("unit", "处");
                set("material", "air");
                set("no_rideto", 1);
                set("no_flyto", 1); 
                set("exits", ([ "out" : "/kungfu/class/sky/sky13" ]));
             
                set("no_get", "!@#$!@#%%^@!^\n");
        }
        setup();
}
/*
void init()
{
        object me = this_player();
        
        add_action("do_start", "start");
        
        CHANNEL_D->do_channel("rumor", this_object(), HIY + me->name() + "(" + me->query("id") + ")" HIM "被炎黄天神送入无尽太虚，挑战二转守护神！\n" NOR);                
}
*/


int valid_leave(object me, string arg)
{
        return 1;
}

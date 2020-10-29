// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m神[1;37m之[1;35m祝福[1;31m火箭[2;37;0m[2;37;0m", ({"wugui"}));        
        set("gender", "男性");                
        set("long", "finish[2;37;0m
它是午夜呼声的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "superjld");
        set("owner_name", "午夜呼声");
        set_temp("owner", "superjld");
        set_temp("owner_name", "午夜呼声");
        ::setup();
}

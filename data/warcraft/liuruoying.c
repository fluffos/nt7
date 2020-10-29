// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m为爱痴狂[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "男性");                
        set("long", "我爱我的龙龙[2;37;0m
它是刘若英的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "liuruoying");
        set("owner_name", "刘若英");
        set_temp("owner", "liuruoying");
        set_temp("owner_name", "刘若英");
        ::setup();
}

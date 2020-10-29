// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m爱的代价[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "男性");                
        set("long", "我爱我的龙龙[2;37;0m
它是张艾嘉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zhangaijia");
        set("owner_name", "张艾嘉");
        set_temp("owner", "zhangaijia");
        set_temp("owner_name", "张艾嘉");
        ::setup();
}

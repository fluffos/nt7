// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("日久生情[2;37;0m[2;37;0m", ({"rii"}));        
        set("gender", "男性");                
        set("long", "日久生情[2;37;0m
它是一次八天的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "skyh");
        set("owner_name", "一次八天");
        set_temp("owner", "skyh");
        set_temp("owner_name", "一次八天");
        ::setup();
}

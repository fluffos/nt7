// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m诸葛亮[2;37;0m[2;37;0m", ({"zgl"}));        
        set("gender", "男性");                
        set("long", "天上地下阿弥陀佛[2;37;0m
它是诸葛不亮的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zgbl");
        set("owner_name", "诸葛不亮");
        set_temp("owner", "zgbl");
        set_temp("owner_name", "诸葛不亮");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m玄龟[2;37;0m[2;37;0m", ({"kkdd"}));        
        set("gender", "男性");                
        set("long", "爽[2;37;0m
它是虐杀丁一的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "kding");
        set("owner_name", "虐杀丁一");
        set_temp("owner", "kding");
        set_temp("owner_name", "虐杀丁一");
        ::setup();
}

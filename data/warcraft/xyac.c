// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m闪[1;32m闪[36m红[1;31m星[2;37;0m[2;37;0m", ({"zhangsan"}));        
        set("gender", "男性");                
        set("long", "高大[2;37;0m
它是天体会的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xyac");
        set("owner_name", "天体会");
        set_temp("owner", "xyac");
        set_temp("owner_name", "天体会");
        ::setup();
}

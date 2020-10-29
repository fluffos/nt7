// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m萌[1;31m爆[1;35m你[1;32m双眼[2;37;0m[2;37;0m[2;37;0m", ({"loveable"}));        
        set("gender", "女性");                
        set("long", "萌爆你双眼！[2;37;0m
它是妹纸贼萌的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cutie");
        set("owner_name", "妹纸贼萌");
        set_temp("owner", "cutie");
        set_temp("owner_name", "妹纸贼萌");
        ::setup();
}

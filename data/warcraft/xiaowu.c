// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火舞[2;37;0m[2;37;0m", ({"huowu"}));        
        set("gender", "女性");                
        set("long", "一只萌萌[2;37;0m
它是小舞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiaowu");
        set("owner_name", "小舞");
        set_temp("owner", "xiaowu");
        set_temp("owner_name", "小舞");
        ::setup();
}

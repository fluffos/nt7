// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是蓝丝的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "moneydmc");
        set("owner_name", "蓝丝");
        set_temp("owner", "moneydmc");
        set_temp("owner_name", "蓝丝");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛛蛛[2;37;0m[2;37;0m", ({"zhuq"}));        
        set("gender", "女性");                
        set("long", "蛛[2;37;0m
它是桃花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "taohua");
        set("owner_name", "桃花");
        set_temp("owner", "taohua");
        set_temp("owner_name", "桃花");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙十八[2;37;0m[2;37;0m", ({"haoh"}));        
        set("gender", "女性");                
        set("long", "这是一条美丽的龙。三围1000 － 500 － 1000[2;37;0m
它是李十八的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "clrak");
        set("owner_name", "李十八");
        set_temp("owner", "clrak");
        set_temp("owner_name", "李十八");
        ::setup();
}

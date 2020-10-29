// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m真爱永恒[2;37;0m[2;37;0m", ({"ilovejuan"}));        
        set("gender", "男性");                
        set("long", "我爱我的娟娟[2;37;0m
它是李龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lilong");
        set("owner_name", "李龙");
        set_temp("owner", "lilong");
        set_temp("owner_name", "李龙");
        ::setup();
}

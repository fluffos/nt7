// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m如是[2;37;0m[2;37;0m", ({"liurss"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是柳如是的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "liurs");
        set("owner_name", "柳如是");
        set_temp("owner", "liurs");
        set_temp("owner_name", "柳如是");
        ::setup();
}

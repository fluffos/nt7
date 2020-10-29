// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m[45m那啥[2;37;0m[2;37;0m", ({"zuesns"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是神尼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesn");
        set("owner_name", "神尼");
        set_temp("owner", "zuesn");
        set_temp("owner_name", "神尼");
        ::setup();
}

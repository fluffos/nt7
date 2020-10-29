// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37;41m六龙[2;37;0m[2;37;0m", ({"zuesfs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是叶六的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesf");
        set("owner_name", "叶六");
        set_temp("owner", "zuesf");
        set_temp("owner_name", "叶六");
        ::setup();
}

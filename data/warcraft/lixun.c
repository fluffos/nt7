// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m七[1;35m彩[1;32m麒[1;34m麟[1;33m王[2;37;0m[2;37;0m", ({"asa"}));        
        set("gender", "女性");                
        set("long", "麒麟一族的至尊王者[2;37;0m
它是小哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lixun");
        set("owner_name", "小哥");
        set_temp("owner", "lixun");
        set_temp("owner_name", "小哥");
        ::setup();
}

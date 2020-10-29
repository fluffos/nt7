// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "dd[2;37;0m
它是干翻高峰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mxa");
        set("owner_name", "干翻高峰");
        set_temp("owner", "mxa");
        set_temp("owner_name", "干翻高峰");
        ::setup();
}

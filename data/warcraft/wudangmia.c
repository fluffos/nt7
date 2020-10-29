// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌当三米麒麟[2;37;0m[2;37;0m", ({"wudangmiaqilin"}));        
        set("gender", "男性");                
        set("long", "乌当三米麒麟[2;37;0m
它是乌当三米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wudangmia");
        set("owner_name", "乌当三米");
        set_temp("owner", "wudangmia");
        set_temp("owner_name", "乌当三米");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("翁翻[2;37;0m[2;37;0m", ({"yznride"}));        
        set("gender", "男性");                
        set("long", "翁翻[2;37;0m
它是杨镇凝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yzn");
        set("owner_name", "杨镇凝");
        set_temp("owner", "yzn");
        set_temp("owner_name", "杨镇凝");
        ::setup();
}

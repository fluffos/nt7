// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m哀牢神兽[2;37;0m[2;37;0m", ({"ailao"}));        
        set("gender", "男性");                
        set("long", "这是哀牢山中的神兽。[2;37;0m
它是段和誉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "heyu");
        set("owner_name", "段和誉");
        set_temp("owner", "heyu");
        set_temp("owner_name", "段和誉");
        ::setup();
}

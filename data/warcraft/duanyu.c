// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m枣红马[2;37;0m[2;37;0m", ({"zaohongma"}));        
        set("gender", "男性");                
        set("long", "枣红马[2;37;0m
它是段誉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "duanyu");
        set("owner_name", "段誉");
        set_temp("owner", "duanyu");
        set_temp("owner_name", "段誉");
        ::setup();
}

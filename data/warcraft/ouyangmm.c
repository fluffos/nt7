// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuq"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是欧阳美眉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ouyangmm");
        set("owner_name", "欧阳美眉");
        set_temp("owner", "ouyangmm");
        set_temp("owner_name", "欧阳美眉");
        ::setup();
}

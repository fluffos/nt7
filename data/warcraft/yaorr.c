// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yaorrr"}));        
        set("gender", "男性");                
        set("long", "日日日[2;37;0m
它是药肉肉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaorr");
        set("owner_name", "药肉肉");
        set_temp("owner", "yaorr");
        set_temp("owner_name", "药肉肉");
        ::setup();
}

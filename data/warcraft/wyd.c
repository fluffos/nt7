// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "小白狗[2;37;0m
它是多哥的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wyd");
        set("owner_name", "多哥");
        set_temp("owner", "wyd");
        set_temp("owner_name", "多哥");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m金轮法王[2;37;0m[2;37;0m", ({"fawang"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIB$金轮法王[2;37;0m
它是狄云的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "diyun");
        set("owner_name", "狄云");
        set_temp("owner", "diyun");
        set_temp("owner_name", "狄云");
        ::setup();
}

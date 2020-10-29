// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m世京[2;37;0m[2;37;0m", ({"taohuadao"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIC$世京[2;37;0m
它是蓝小邪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mpygthd");
        set("owner_name", "蓝小邪");
        set_temp("owner", "mpygthd");
        set_temp("owner_name", "蓝小邪");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m跳舞的朱雀[2;37;0m[2;37;0m", ({"qingwu"}));        
        set("gender", "女性");                
        set("long", "$HIM$天使之翼[2;37;0m
它是舞步的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wubu");
        set("owner_name", "舞步");
        set_temp("owner", "wubu");
        set_temp("owner_name", "舞步");
        ::setup();
}

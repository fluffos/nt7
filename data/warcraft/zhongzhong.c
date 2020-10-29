// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zzza"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是中笑的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zhongzhong");
        set("owner_name", "中笑");
        set_temp("owner", "zhongzhong");
        set_temp("owner_name", "中笑");
        ::setup();
}

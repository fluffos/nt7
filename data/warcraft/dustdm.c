// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m江户四十八手[2;37;0m[2;37;0m", ({"dustmm"}));        
        set("gender", "男性");                
        set("long", "$HIY$江户四十八手[2;37;0m
它是客官米米的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dustdm");
        set("owner_name", "客官米米");
        set_temp("owner", "dustdm");
        set_temp("owner_name", "客官米米");
        ::setup();
}

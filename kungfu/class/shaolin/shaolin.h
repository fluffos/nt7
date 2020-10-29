// shaolin.h

int permit_recruit(object ob)
{
        if( query("detach/少林派", ob) || 
            query("betrayer/少林派", ob) )
        {
                command("say 你反反复复，唉！怎么一心向佛？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 你大逆不道，私自判师，不能容于少林！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "少林派" )
        {
                command("say 你已经名师指点，为何不下苦功，反而来我们"
                        "少林寺呢？");
                return 0;
        }

        return 1;
}

// hengshan.h

int permit_recruit(object ob)
{
        command("say 恒山派暂不开放。");
        return 0;
        if( query("detach/恒山派", ob) || query("betrayer/恒山派", ob) )
        {
                command("say 你当年都已经离开了恒山派，何必又要回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我们恒山派乃名门正派，决不收判师之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "恒山派" )
        {
                command("say 你既然已经有了名师指点，不好好学习，来我们恒山派作甚？");
                return 0;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 阿弥陀佛！贫尼不收俗家弟子。");
                return 0;
        }

        if( query("gender", ob) != "女性" )
        {
                command("say 阿弥陀佛！贫尼不收男弟子。");
                return 0;
        }

        return 1;
}

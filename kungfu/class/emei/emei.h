// emei.h

int permit_recruit(object ob)
{
        object me;

        me = this_object();
        if( query("detach/峨嵋派", ob) || 
            query("betrayer/峨嵋派", ob) )
        {
                command("say 你当年既然离开了峨嵋派，今天又何必回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 你欺师灭主，背叛师门，"
                        "这种人我们峨嵋派不会收留的。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "峨嵋派" )
        {
                command("say 你已有名师指点，为何又来峨嵋派？"
                        "莫非你要判师不成？");
                return 0;
        }

        if( query("class", me) == "bonze" )
        {
                if( query("class", ob) != "bonze" )
                {
                        command("say 阿弥陀佛！贫尼不收俗家弟子。");
                        command("say 你若想继续学峨嵋派的功夫，"
                                "还是去找我俗家师妹吧。");
                        return 0;
                }

                if( query("gender", ob) != "女性" )
                {
                        command("say 阿弥陀佛！贫尼不收男弟子。"
                                "施主若想学艺可去找我俗家师妹。");
                        return 0;
                }
        }

        if( query("shen", ob)<0 )
        {
                command("say 唉，你现在正入歧途，我怎能收你为徒？");
                return 0;
        }

        return 1;
}

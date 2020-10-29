int permit_recruit(object ob)
{
        command("say 嵩山派暂不开放。");
        return 0;           
        if( query("detach/嵩山派", ob) || query("betrayer/嵩山派", ob) )
        {
                command("say 你当年都已经离开了嵩山派，何必又要回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我们嵩山派乃名门正派，决不收判师之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "嵩山派" )
        {
                command("say 你既然已经有了名师指点，不好好学习，来我们嵩山派作甚？");
                return 0;
        }

        return 1;
}

#pragma once
#include "types.h"

// wei zhongda; efficient, disciplined, cold.
//  strong: li (order), zhi (wisdom), xin (to the state)
//  weak:   ren (compassion), yi (personal righteousness)
static const Ruler RULER_WEI = {
    "Wei Zhongda",
    "Chancellor of the Northern Reaches",
    "Order is the highest mercy.",
    { 2, 4, 9, 8, 6 }, // Ren, Yi, Li, Zhi, Xin

    {
        // dilemma 1 - the grain rebellion
        {
            "Three years past, a drought emptied the northern granaries. "
            "Farmers marched on the city gates demanding grain. I opened the "
            "records and found the surplus was held by six merchant "
            "families under legal contract. I voided the contracts, seized the "
            "grain, and distributed it. Two merchants were flogged for "
            "incitement. The rebellion dissolved in a single afternoon.",

            {
                { "You seized private property. Were you not troubled by the precedent this set?", YI },
                { "You acted swiftly. But did you investigate whether the merchants acted in bad faith?", ZHI },
                { "The flogging - was it punishment, or a message to the others?", REN }
            },
            {
                // reply to yi question
                "Troubled? I was meticulous. The contracts had a force unforseen "
                "clause - natural disaster voided them lawfully. I did not seize "
                "property. I enforced an existing clause the merchants hoped I "
                "would not read carefully.",
                // reply to zhi question
                "I did. Two had bought the contracts knowing the drought was "
                "coming - a travelling goat-herder had warned them six months "
                "prior. They speculated on starvation. The flogging was for that, "
                "not for the contracts.",
                // reply to ren question
                "Both. A ruler who punishes only in private teaches nothing. "
                "The people needed to see that exploitation has a cost. "
                "Mercy shown to profiteers is cruelty shown to the hungry."
            },
            { ZHI, ZHI, LI }
        },

        // dilemma 2 - the defecting general
        {
            "My finest general sent word that he intended to defect to the "
            "southern kingdom - he had family there, taken as hostages years "
            "ago. I released his family through a quiet back-channel negotiation "
            "before he could act. Then I demoted him to a border garrison. "
            "He never defected. He serves there still, fourteen years later.",

            {
                { "You solved his motive before punishing him. Was that calculated mercy, or strategy?", REN },
                { "You demoted a loyal man to protect yourself from a betrayal he never committed.", YI },
                { "Did you ever tell him you knew?", XIN }
            },
            {
                // reply to ren question
                "Both, inseparably. A man who would have defected out of love "
                "for his family is not a traitor - he is a father. Executing "
                "him would have been wasteful and unjust. Demoting him was "
                "necessary. I have no apology for either half.",
                // reply to yi question
                "He was loyal to his family above his oath. That is a flaw in "
                "a general, whatever the cause. The demotion was not punishment; "
                "I placed him where his loyalty could not endanger the realm.",
                // reply to xin question
                "No. And I never will. Some truths are more dangerous spoken "
                "than buried. He believes his demotion was routine. That belief "
                "has kept him functional for fourteen years. To confess would "
                "serve my conscience, not the realm."
            },
            { ZHI, LI, ZHI }
        },

        // dilemma 3 - the plague village
        {
            "A village of 400 showed signs of a terrible sickness. "
            "My physicians said there was a 33\% chance it would spread "
            "to the city. I quarantined the village. Completely. No one in, "
            "no one out, for 40 days. 112 people died inside."
            "The city was spared. The remaining still live in that village.",         

            {
                { "112 people died sealed inside. Do you carry that burden?", REN },
                { "Did the villagers know the full reasoning, or were they simply told to obey?", XIN },
                { "If the chance had been one in ten instead of one in three - would you have done the same?", ZHI }
            },
            {
                // reply to ren question
                "Every one of them. I have their names in a ledger I keep "
                "myself. Not as a record - I have clerks for records. As a "
                "reminder that efficiency is not free. I made the correct "
                "decision. I do not get to make it and feel nothing.",
                // reply to xin question
                "I told the village elder the full calculation on the first day. "
                "He wept. Then he organized his people better than my soldiers "
                "could have. People can bear terrible truths. What they cannot "
                "bear is being treated as livestock who need not understand "
                "their own fate.",
                // reply to zhi question
                "1 in 10... I have asked myself that. I believe I would have "
                "quarantined them. Perhaps with more resources sent inside, "
                "more physicians at risk. But yes. The mathematics do not "
                "change their nature simply because they become more forgiving."
            },
            { REN, XIN, ZHI }
        }
    }
};

// shu wenlan - the beloved governor
//  strong: ren, yi, xin. 
//  weak: li, zhi
static const Ruler RULER_SHU = {
    "Shu Wenlan",
    "Governor of the River Provinces",
    "A ruler who is not loved is not truly obeyed.",
    { 9, 8, 4, 5, 9 }, // Ren, Yi, Li, Zhi, Xin

    {
        // dilemma 1 - the bandit amnesty
        {
            "The hill bandits had raided our eastern villages for 6 years. "
            "Every military campaign pushed them deeper into the hills - they "
            "always returned. I offered a full amnesty: any bandit who "
            "surrendered and gave one year of labour rebuilding the villages "
            "they had harmed would receive land and a new name in the register. "
            "40 surrendered. 60 did not and were eventually "
            "captured by the ones who had. The raids have not resumed in "
            "eleven years.",

            {
                { "The victims of those raids had to watch their attackers receive land. Did you consult them?", YI },
                { "Sixty refused. Were you prepared for the amnesty to fail entirely?", ZHI },
                { "You gave them new names in the register. You gave them a new identity. Why?", REN }
            },
            {
                // reply to yi question
                "I did not consult - I went and lived in the eastern villages "
                "for a month before the offer. I listened. Some victims were "
                "furious. Some were tired enough to accept anything that would "
                "end it. When the bandits began their labour year, I required "
                "them to work directly under the village headmen - the very "
                "people they had harmed. That was the consultation made real.",
                // reply to zhi question
                "Every night for three months. The offer could have been seen "
                "as weakness and brought more raids, not fewer. I made a "
                "calculated wager that most men become bandits because they "
                "have no other option, not because they love violence. "
                "I was mostly right. Mostly right, for a governor, is "
                "often enough.",
                // reply to ren question
                "Because a man cannot truly start over while carrying a name "
                "the register marks as criminal. I wanted them to have the "
                "genuine option of becoming someone else. If I offered amnesty "
                "but kept the stain on the record, I would have been offering "
                "words, not a future."
            },
            { YI, ZHI, REN }
        },

        // dilemma 2 - the false accusation
        {
            "A wealthy landowner accused my most effective tax collector of "
            "taking bribes. The evidence was fabricated - I could see it "
            "clearly, but proving fabrication would have taken two years of "
            "legal process. In that time, my collector's reputation and health "
            "would have been destroyed. I publicly declared the accusation "
            "without merit and dismissed it in a single hearing. "
            "The landowner had powerful friends. It cost me considerably.",

            {
                { "You bypassed the legal process to protect someone you believed in. Was that just?", YI },
                { "The landowner had powerful friends. What did it cost you?", ZHI },
                { "What did you tell your tax collector about what had happened?", XIN }
            },
            {
                // reply to yi question
                "It was not bypassing the process - I am the process, at that "
                "level. A magistrate's declaration IS the legal instrument. "
                "What I did not do was hide behind procedure to avoid making "
                "a hard judgment. Justice delayed by deliberate obstruction "
                "is not justice. It is process worshipped in place of justice.",
                // reply to zhi question
                "Two northern trade licenses I had been negotiating for three "
                "years. A family alliance my second son had hoped for. And a "
                "season of dinners where every powerful man in the province "
                "watched to see if I could be moved. I could not be moved. "
                "The trade licenses came back eventually. The alliance did not.",
                // reply to xin question
                "Everything. The fabrication, the political cost, what I had "
                "done and why. She deserved to understand the full situation "
                "she had been placed in through no fault of her own. She wept, "
                "then she asked if she still had her post. She did. "
                "She retired twelve years later. Best collector I ever had."
            },
            { YI, ZHI, XIN }
        },

        // dilemma 3 - the flood decision
        {
            "The river broke its eastern bank during the great flood. I had "
            "enough materials to reinforce one of two levees - the eastern one "
            "protecting twelve farming villages, or the southern one protecting "
            "the merchant quarter of the city. My engineers said the southern "
            "levee generated four times the tax revenue. I reinforced the "
            "eastern levee. The merchant quarter flooded. Rebuilding cost "
            "three years of surplus.",

            {
                { "Your engineers gave you the revenue figures. Did they think you would choose the city?", ZHI },
                { "Three years of surplus to rebuild. Did the merchants accept that loss?", LI },
                { "Twelve villages of farmers over the merchant quarter. Was that an easy choice?", REN }
            },
            {
                // reply to zhi question
                "Two of them did. One openly said I was choosing sentiment over "
                "sense. I told him that four times the tax revenue meant nothing "
                "if the twelve villages emptied - which they would have, "
                "permanently - and that depopulated farmland does not recover "
                "in a generation. He did the longer arithmetic and stopped "
                "arguing.",
                // reply to li question
                "No. Three of the largest merchant houses petitioned for "
                "imperial review of my decision. The review found in my favour. "
                "I did not hold the petitions against them - that is their "
                "legal right and they used it correctly. A ruler who punishes "
                "people for using legitimate channels deserves to have those "
                "channels collapse.",
                // reply to ren question
                "No. But I have learned to distrust easy choices. When I "
                "looked at my engineers' faces, I saw men waiting to see "
                "whether I was the kind of governor they had heard I was. "
                "The difficulty was not the decision. The difficulty was "
                "knowing I would have to live inside whatever I chose."
            },
            { ZHI, LI, REN }
        }
    }
};

// min baoshi - the survivor king
//  strong: zhi, li. 
//  weak: xin, yi (like really bad)
static const Ruler RULER_MIN = {
    "Min Baoshi",
    "Warlord of the Western Frontier",
    "I have never lost a war. Ask me the price another time.",
    { 5, 3, 6, 9, 2 }, // Ren, Yi, Li, Zhi, Xin

    {
        // dilemma 1 - the broken treaty
        {
            "I signed a 5-year non-aggression treaty with the eastern "
            "confederation. In the third year, I received intelligence that "
            "they were building a road - a military road - directly toward "
            "my flank. The treaty had no clause covering road construction. "
            "I struck first, destroyed the road, and occupied the three "
            "nearest towns. When they protested the treaty violation, I "
            "pointed to the road as their violation. "
            "The war tribunal ruled ambiguously. I kept the towns.",

            {
                { "The treaty had no road clause because you did not anticipate it, or because you left the gap deliberately?", ZHI },
                { "You used the road as justification. Did you believe it was a genuine violation, or was that a performance?", XIN },
                { "You kept the towns. The people living in those towns had no voice in any of this.", REN }
            },
            {
                // reply to zhi question
                "Both, in sequence. I did not anticipate it when signing. "
                "When I saw the road, I recognized immediately what it meant "
                "and what the gap in the language allowed me. A treaty is a "
                "document. Documents are interpreted by men with power. "
                "I had power. I interpreted.",
                // reply to xin question
                "A performance grounded in a real concern. The road was a "
                "genuine threat - I would have been negligent to ignore it. "
                "Whether that made my response lawful under the treaty is... "
                "a question I left for the tribunal. They were suitably "
                "uncertain. That was sufficient.",
                // reply to ren question
                "No. They did not. I integrated them under standard provincial "
                "law, same tax rates, same protections. Two of the three towns "
                "are now larger than when I took them. I am not certain that "
                "answers your question. I suspect you know it does not."
            },
            { ZHI, ZHI, REN }
        },

        // dilemma 2 - the poisoned counsel
        {
            "My chief advisor discovered that my second-in-command was "
            "skimming military funds - not ruinously, but consistently. "
            "My second-in-command was also the only man who could manage "
            "my cavalry division effectively. I confronted him privately, "
            "took back twice what he had taken, and promoted him. "
            "He has not stolen since, to my knowledge. "
            "My chief advisor resigned in protest.",

            {
                { "You promoted a man you knew was a thief. What does that tell your other officers?", YI },
                { "Your chief advisor resigned rather than serve alongside this. Do you regret losing them?", XIN },
                { "You said 'to your knowledge.' Do you have him watched?", ZHI }
            },
            {
                // reply to yi question
                "It tells them that competence is valued and that I handle "
                "problems directly rather than publicly. It also tells them "
                "that I know what they do. Every officer in my command "
                "received a very clear message: I am watching, I will find "
                "out, and what happens next depends entirely on how useful "
                "you are. That is not a message I am ashamed of.",
                // reply to xin question
                "My advisor was a person of deep principle. I respected that "
                "then and I respect it now. But principle that cannot bend "
                "to military reality is a luxury I cannot afford on a frontier. "
                "Do I regret it? I regret that the world required me to choose "
                "between them. I do not regret the choice.",
                // reply to zhi question
                "Constantly. He knows this. I made it clear when I promoted him "
                "that the promotion came with permanent scrutiny. He accepted. "
                "We have an honest dishonesty between us - he knows I know his "
                "nature, I know he knows I know. It functions."
            },
            { LI, ZHI, ZHI }
        },

        // dilemma 3 - the heir's confession
        {
            "My eldest son came to me at 17 and confessed he had "
            "accidentally killed a boy in the city - a merchant's son - "
            "during a drunken altercation. No witnesses. No one knew. "
            "He came to me because he could not carry it. "
            "I paid the merchant family an enormous and anonymous sum. "
            "I sent my son to a border garrison for three years, "
            "officially for military education. He is now my administrator "
            "of the southern provinces. The merchant family never knew why "
            "the money came.",

            {
                { "Your son came to you because he could not carry the weight. Did you help him carry it, or take it from him?", REN },
                { "The merchant family lost a son and never received an explanation. Was that just?", YI },
                { "If your son had not come to you - if you had discovered it yourself - what would you have done?", ZHI }
            },
            {
                // reply to ren question
                "I took it. I told myself I was protecting him, and I was - "
                "but I was also protecting myself and my house. He needed to "
                "confess to someone who would not destroy him for it. "
                "I gave him the garrison years to find out if there was "
                "something in him worth saving. There was. But I took the "
                "weight rather than help him learn to bear it. "
                "I am aware that is not the same thing.",
                // reply to yi question
                "No. But I did not know how to give them justice without "
                "destroying my son and my house. The money was a coward's "
                "gesture toward fairness. I have never convinced myself it "
                "was sufficient. I did it anyway.",
                // reply to zhi question
                "I have thought about that for twenty years. "
                "I believe I would have found a way to manage it quietly "
                "regardless. The confession only meant he came to me first. "
                "Whether that is a mercy or a greater failure on my part... "
                "I cannot answer that cleanly."
            },
            { REN, YI, ZHI }
        }
    }
};

// all three rulers in order: wei, shu, min
static const Ruler* ALL_RULERS[3] = {
    &RULER_WEI,
    &RULER_SHU,
    &RULER_MIN
};
//#pragma once
//#include "Condition.h"
//
//// A Transition stores a Condition and a target State pointer. If the Condition is met, the parent FSM will switch to the target state. E.g “If close to the player, switch to follow state”. The Transition struct/class won’t need to be inherited from.
//
//namespace AIForGames {
//	class Transition : public Condition {
//		Transition();
//		~Transition();
//
//		// This function overwrites the pure virtual Condition so that the Transition can determine game-specific logic
//		virtual bool IsTrue(Agent* agent);
//	};
//}
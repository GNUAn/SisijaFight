// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CLogger.h"
#include <iostream>
#include <string>

namespace irr
{

	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string BLUE = "\033[34m";
	const std::string MAGENTA = "\033[35m";
	const std::string CYAN = "\033[36m";
	const std::string RESET = "\033[0m";

	CLogger::CLogger(IEventReceiver* r)
		: LogLevel(ELL_INFORMATION), Receiver(r)
	{
		#ifdef _DEBUG
		setDebugName("CLogger");
		#endif
	}

	//! Returns the current set log level.
	ELOG_LEVEL CLogger::getLogLevel() const
	{
		return LogLevel;
	}

	//! Sets a new log level.
	void CLogger::setLogLevel(ELOG_LEVEL ll)
	{
		LogLevel = ll;
	}

	//! Prints out a text into the log
	void CLogger::log(const c8* text, ELOG_LEVEL ll, const char* caller)
	{
		if (ll < LogLevel)
			return;

		if (Receiver)
		{
			SEvent event;
			event.EventType = EET_LOG_TEXT_EVENT;
			event.LogEvent.Text = text;
			event.LogEvent.Level = ll;
			if (Receiver->OnEvent(event))
				return;
		}
		switch (ll) {
		case ELL_DEBUG:
			std::cout << CYAN;
			break;
		case ELL_ERROR:
			std::cout << RED;
			break;
		case ELL_INFORMATION:
			std::cout << BLUE;
			break;
		case ELL_WARNING:
			std::cout << YELLOW;
		case ELL_NONE:
			std::cout << MAGENTA;
			break;
		}
		std::cout << "[" << caller << "]: " << text << RESET << std::endl;
		
	}


	//! Prints out a text into the log
	void CLogger::log(const c8* text, const c8* hint, ELOG_LEVEL ll)
	{
		if (ll < LogLevel)
			return;

		std::string s = "IrrlichtEngine, ";
		s += hint;

		log (text, ll, s.c_str());
	}

	//! Prints out a text into the log
	void CLogger::log(const wchar_t* text, ELOG_LEVEL ll)
	{
		if (ll < LogLevel)
			return;

		core::stringc s = text;
		log(s.c_str(), ll, "IrrlichtEngine");
	}


	//! Prints out a text into the log
	void CLogger::log(const wchar_t* text, const wchar_t* hint, ELOG_LEVEL ll)
	{
		if (ll < LogLevel)
			return;

		core::stringc s1 = text;
		core::stringc s2 = hint;
		log(s1.c_str(), s2.c_str(), ll);
	}

	//! Prints out a text into the log
	void CLogger::log(const c8* text, const wchar_t* hint, ELOG_LEVEL ll)
	{
		if (ll < LogLevel)
			return;

		core::stringc s2 = hint;
		log( text, s2.c_str(), ll);
	}

	//! Sets a new event receiver
	void CLogger::setReceiver(IEventReceiver* r)
	{
		Receiver = r;
	}


} // end namespace irr


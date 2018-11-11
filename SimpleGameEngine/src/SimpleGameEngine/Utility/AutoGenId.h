#pragma once

namespace SimpleGameEngine::Utility
{
	/// <summary>
	/// This is a 'hack' class that automatically generates an ID
	/// each time a class is constructed.
	/// </summary>
	/// <remarks>
	/// This is mainly used to provide a really bad 'hash' for objects
	/// so they can be used in STL classes (e.g. std::map)
	/// </remarks>
	class AutoGenId
	{
	private:
		static unsigned int s_id;
		unsigned int m_id;

	public:
		AutoGenId();
		AutoGenId(const AutoGenId & other);
		virtual ~AutoGenId();

		/// <summary>
		/// --- HACK ---
		/// <para></para>
		/// Gets the ID of this object.
		/// </summary>
		/// <returns></returns>
		unsigned int ___getObjectId() const;



		AutoGenId & operator=(const AutoGenId & other);
	};
}

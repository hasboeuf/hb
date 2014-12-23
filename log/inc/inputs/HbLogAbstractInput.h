#ifndef HBLOGABSTRACTINPUT_H
#define HBLOGABSTRACTINPUT_H

#include <IHbLoggerInput.h>

namespace hb
{
	namespace log
	{
		class HbLogAbstractInput :
            public virtual IHbLoggerInput
		{
            Q_DISABLE_COPY( HbLogAbstractInput )

		public :

            virtual ~HbLogAbstractInput() = default;
			virtual InputType type() const final;

        protected :

            HbLogAbstractInput() = delete;
            HbLogAbstractInput( InputType type );

        private :
            InputType mType;
		};
	}
}

#endif
